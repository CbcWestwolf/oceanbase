/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#define USING_LOG_PREFIX SHARE

#include "ob_external_tok_iterator.h"

namespace oceanbase {
namespace share {

int ObExternalTokenIterator::inner_get_next_row(ObNewRow*& row)
{
  int ret = OB_SUCCESS;
  ObSEArray<ObString, 16> tokens;
  char* token = nullptr;
  const int total_column_cnt = table_schema_->get_column_count() - (table_schema_->is_no_pk_table() ? 1 : 0);

  LOG_DEBUG("read buffer", K(data_source_.buffer.ptr_), K(data_source_.buffer.buf_size_));
  LOG_DEBUG("tokens_", K(tokens_));

  // 获取 data_source_.buffer.ptr_
  if (OB_ISNULL(data_source_.buffer.ptr_)) {
    if (!external_loader_->has_next()) {
      ret = OB_ITER_END;
    } else if (OB_FAIL(external_loader_->read(data_source_))) {
      LOG_WARN("fail to read data", K(ret));
    }
    tokens_ = data_source_.buffer.ptr_;
  }

  if (OB_SUCC(ret)) {

    // 跳过 offset
    while (OB_SUCC(ret) && limit_param_.offset_-- > 0 && OB_NOT_NULL(tokens_) && strlen(tokens_) > 0) {
      for (int i = 0; i < total_column_cnt && OB_SUCC(ret) && OB_NOT_NULL(tokens_) && strlen(tokens_) > 0; ++i) {
        token = strtok_r(nullptr, field_delimiter_.ptr(), &tokens_);
      }
    }

    if (OB_ISNULL(tokens_) || strlen(tokens_) == 0) {
      ret = OB_ITER_END;
    }
  }

  // 检查 limit
  if (OB_SUCC(ret) && limit_param_.limit_ != -1 && (limit_param_.limit_-- == 0)) {
    ret = OB_ITER_END;
  }

  if (OB_SUCC(ret)) {
    for (int i = 0; i < total_column_cnt && OB_SUCC(ret) && OB_NOT_NULL(tokens_) && strlen(tokens_) > 0; ++i) {
      token = strtok_r(nullptr, field_delimiter_.ptr(), &tokens_);
      ret = tokens.push_back(ObString(token));
      LOG_DEBUG("token", K(token));
    }
  }

  if (OB_SUCC(ret)) {
    const ObDataTypeCastParams dtc_params =
        sql::ObSQLSessionInfo::create_dtc_params(static_cast<const sql::ObBasicSessionInfo*>(session_));
    ObCastCtx cast_ctx(allocator_, &dtc_params, CM_NONE, ObCharset::get_system_collation());
    ObObj* cells = NULL;

    if (OB_ISNULL(cells = static_cast<ObObj*>(allocator_->alloc(scan_cols_schema_.count() * sizeof(ObObj))))) {
      ret = OB_ALLOCATE_MEMORY_FAILED;
      LOG_WARN("fail to alloc new obj", K(ret));
    } else if (OB_ISNULL(cells = new (cells) ObObj[scan_cols_schema_.count()])) {
      ret = OB_ALLOCATE_MEMORY_FAILED;
      LOG_WARN("fail to construct new obj", K(ret));
    }

    for (int64_t i = 0; OB_SUCC(ret) && i < scan_cols_schema_.count(); ++i) {
      const share::schema::ObColumnSchemaV2* col_schema = scan_cols_schema_.at(i);
      int index = table_schema_->get_column_idx(col_schema->get_column_id(), true);
      if (index >= table_schema_->get_column_count()) {
        ret = OB_ERR_UNEXPECTED;
        LOG_WARN("column index larger than column's num", K(index), K(table_schema_->get_column_count()));
      } else {
        ObObjType dest_type = scan_cols_schema_.at(i)->get_meta_type().get_type();
        ObObj in_obj;
        ObObj out_obj;
        in_obj.set_varchar(tokens.at(index));
        in_obj.set_collation_type(ObCharset::get_system_collation());
        if (OB_FAIL(ObObjCaster::to_type(dest_type, ObCharset::get_system_collation(), cast_ctx, in_obj, out_obj))) {
          LOG_WARN("fail to cast obj", K(ret), K(dest_type), K(cast_ctx), K(in_obj), K(out_obj));
        } else {
          cells[i] = out_obj;
        }
      }
    }
    if (OB_SUCC(ret)) {
      cur_row_.cells_ = cells;
      cur_row_.count_ = scan_cols_schema_.count();
      row = &cur_row_;
    }
  }

  return ret;
}

void ObExternalTokenIterator::reset()
{
  /*
  char* tokens_;
  ObString field_delimiter_;
  */
  tokens_ = nullptr;
  field_delimiter_.reset();
  ObExternalTableIterator::reset();
}

int ObExternalTokenIterator::set_table_schema(const share::schema::ObTableSchema* table_schema)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(ObExternalTableIterator::set_table_schema(table_schema))) {
    LOG_WARN("fail to set table schema", K(table_schema));
  }

  field_delimiter_ = table_schema->get_field_delimiter();

  return ret;
}
}  // namespace share
}  // namespace oceanbase