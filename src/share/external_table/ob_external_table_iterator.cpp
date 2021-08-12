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

#include "ob_external_table_iterator.h"
#include "sql/session/ob_sql_session_info.h"
#include "sql/engine/ob_operator.h"

using oceanbase::sql::ObOperator;

namespace oceanbase {
namespace share {

int ObExternalTableIterator::open()
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(external_loader_->open(table_schema_))) {
    LOG_WARN("fail to open", K(table_schema_), K(ret));
  }

  return ret;
}

void ObExternalTableIterator::reset()
{
  scan_param_ = NULL;
  scan_cols_schema_.reset();
  if (OB_LIKELY(NULL != allocator_ && NULL != cur_row_.cells_)) {
    allocator_->free(cur_row_.cells_);
  }
  cur_row_.cells_ = NULL;
  cur_row_.count_ = 0;
  table_schema_ = NULL;
  data_source_.buffer.ptr_ = nullptr;
  data_source_.buffer.buf_size_ = 0;
  data_source_.other_handler_ = nullptr;
  external_loader_->reset();
}

int ObExternalTableIterator::close()
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(inner_close())) {
    LOG_WARN("fail to execute inner close", K(ret));
  } else {
    if (OB_ISNULL(allocator_)) {
      ret = OB_ERR_UNEXPECTED;
      LOG_WARN("allocator is NULL", K(ret));
    } else {
      // Since ObObj's destructor does not do meaningful operations, in order to save performance, ObObj's destructor
      // call is omitted, and the cells_memory is directly released.
      allocator_->free(cur_row_.cells_);
      cur_row_.cells_ = NULL;
      cur_row_.count_ = 0;
      scan_cols_schema_.reset();
    }
  }
  return ret;
}

int ObExternalTableIterator::inner_close()
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(external_loader_->close())) {
    LOG_WARN("fail to close", K(ret));
  }
  return ret;
}

/*
int ObExternalTableIterator::inner_get_next_row(ObNewRow*& row)
{
  int ret = OB_SUCCESS;
  char buf[BUF_SIZE];
  char* token = NULL;
  ObSEArray<ObString, 16> tokens;

  if (OB_ISNULL(fp_)) {
    ret = OB_FILE_NOT_OPENED;
    LOG_WARN("file not open", K(ret), K(fp_));
  } else if (OB_FAIL(skip_offset())) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("fail to skip offset", K(ret));
  } else if (limit_param_.limit_ != -1 && (limit_param_.limit_-- == 0)) {
    ret = OB_ITER_END;
  } else if (feof(fp_)) {
    ret = OB_ITER_END;
  } else if (OB_ISNULL(fgets(buf, BUF_SIZE, fp_))) {
    ret = OB_ITER_END;
  } else {
    size_t end = strcspn(buf, "\n");
    if (end <= 0 || end > strlen(buf)) {
      ret = OB_ERR_UNEXPECTED;
      token = buf;
      LOG_WARN("no nextline", K(token), K(ret));
    } else {
      buf[end] = 0;
      token = strtok(buf, delimiter_);
    }
    while (OB_SUCC(ret) && NULL != token) {
      ret = tokens.push_back(ObString(token));
      token = strtok(NULL, delimiter_);
    }
    if (OB_FAIL(ret) || tokens.count() < scan_cols_schema_.count() ||
        tokens.count() != table_schema_->get_column_count() - (table_schema_->is_no_pk_table() ? 1 : 0)) {
      ret = OB_ERR_UNEXPECTED;
      LOG_WARN("columns number not macth", K(tokens.count()), K(scan_cols_schema_.count()));
    }

    if (OB_SUCC(ret)) {
      const ObDataTypeCastParams dtc_params = sql::ObSQLSessionInfo::create_dtc_params(session_);
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
  }

  return ret;
}
*/

int ObExternalTableIterator::get_next_row(ObNewRow*& row)
{
  int ret = OB_SUCCESS;
  ObNewRow* cur_row = NULL;
  if (OB_FAIL(inner_get_next_row(cur_row))) {
    if (OB_UNLIKELY(OB_ITER_END != ret)) {
      LOG_WARN("fail to inner get next row", K(ret));
    }
  } else if (OB_ISNULL(cur_row)) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("succ to inner get next row, but row is NULL", K(ret));
  } else if (OB_UNLIKELY(cur_row->count_ != scan_cols_schema_.count())) {
    ret = OB_ERR_UNEXPECTED;
    LOG_ERROR("row count is less than output column count", K(ret), K(cur_row->count_), K(scan_cols_schema_.count()));
  } else if (OB_ISNULL(cur_row->cells_)) {
    ret = OB_ERR_UNEXPECTED;
    LOG_ERROR("cur_row->cells_ is NULL", K(ret));
  } else if (OB_ISNULL(table_schema_)) {
    ret = OB_ERR_UNEXPECTED;
    LOG_ERROR("table schema is NULL", K(ret));
  } else {
    for (int64_t i = 0; OB_SUCC(ret) && i < scan_cols_schema_.count(); ++i) {
      const share::schema::ObColumnSchemaV2* col_schema = scan_cols_schema_.at(i);
      if (OB_ISNULL(col_schema)) {
        ret = OB_ERR_UNEXPECTED;
        LOG_ERROR("col_schema is NULL", K(ret), K(i));
      } else if (OB_UNLIKELY(col_schema->get_data_type() != cur_row->cells_[i].get_type() &&
                             ObNullType != cur_row->cells_[i].get_type())) {
        ret = OB_ERR_UNEXPECTED;
        LOG_WARN("column type in this row is not expected type",
            K(ret),
            K(i),
            "table_name",
            table_schema_->get_table_name_str(),
            "column_name",
            col_schema->get_column_name_str(),
            K(cur_row->cells_[i]),
            K(col_schema->get_data_type()),
            K(scan_cols_schema_));
      }
    }
  }

  if (OB_SUCC(ret)) {
    row = cur_row;
  }

  return ret;
}

int ObExternalTableIterator::get_next_row()
{
  int ret = OB_SUCCESS;
  ObNewRow* row = NULL;

  if (OB_ISNULL(scan_param_) || OB_ISNULL(scan_param_->output_exprs_) || OB_ISNULL(scan_param_->op_)) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret));
  }

  while (OB_SUCC(ret)) {
    if (OB_FAIL(get_next_row(row))) {
      if (OB_ITER_END != ret) {
        LOG_WARN("get next row failed", K(ret));
      }
    } else if (OB_ISNULL(row)) {
      LOG_WARN("NULL row returned", K(ret));
    } else if (scan_param_->output_exprs_->count() != row->count_) {
      ret = OB_ERR_UNEXPECTED;
      LOG_WARN(
          "row count less than output exprs", K(ret), K(*row), "output_exprs_cnt", scan_param_->output_exprs_->count());
    } else {
      /* 在这里实现 filter */
      bool filtered = false;
      for (int64_t i = 0; OB_SUCC(ret) && i < scan_param_->output_exprs_->count(); i++) {
        sql::ObExpr* expr = scan_param_->output_exprs_->at(i);
        sql::ObDatum& datum = expr->locate_datum_for_write(scan_param_->op_->get_eval_ctx());
        if (OB_FAIL(datum.from_obj(row->cells_[i], expr->obj_datum_map_))) {
          LOG_WARN("convert ObObj to ObDatum failed", K(ret));
        }
      }
      if (OB_NOT_NULL(scan_param_->op_filters_) && !scan_param_->op_filters_->empty()) {
        LOG_DEBUG("filters count", K(scan_param_->op_filters_->count()));
        for (int64_t i = 0; OB_SUCC(ret) && i < scan_param_->op_filters_->count(); i++) {
          if (OB_FAIL(scan_param_->op_->filter_row_outside(false, *(scan_param_->op_filters_), filtered))) {
            LOG_WARN("filter row failed", K(ret));
          } else {
            if (filtered) {
              break;
            }
          }
        }
      }
      if (!filtered) {

        break;
      }
    }
  }

  return ret;
}

int ObExternalTableIterator::set_scan_param(ObVTableScanParam* scan_param)
{
  int ret = OB_SUCCESS;
  if (OB_ISNULL(scan_param)) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("scan_param is NULL", K(ret));
  } else {
    scan_param_ = scan_param;
    allocator_ = scan_param->scan_allocator_;
  }
  return ret;
}

int ObExternalTableIterator::set_table_schema(const share::schema::ObTableSchema* table_schema)
{
  int ret = OB_SUCCESS;
  table_schema_ = table_schema;
  if (OB_ISNULL(scan_param_) || OB_ISNULL(table_schema)) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("params is NULL", K(ret), K(table_schema), K(scan_param_));
  } else {
    for (int64_t i = 0; OB_SUCC(ret) && i < scan_param_->column_ids_.count(); ++i) {
      const uint64_t column_id = scan_param_->column_ids_.at(i);
      const schema::ObColumnSchemaV2* col_schema = table_schema_->get_column_schema(column_id);
      if (OB_ISNULL(col_schema)) {
        ret = OB_ERR_UNEXPECTED;
        LOG_ERROR("col_schema is NULL", K(ret), K(column_id));
      } else if (OB_FAIL(scan_cols_schema_.push_back(col_schema))) {
        LOG_WARN("failed to push back column schema", K(ret));
      }
    }
  }
  return ret;
}

}  // namespace share
}  // namespace oceanbase