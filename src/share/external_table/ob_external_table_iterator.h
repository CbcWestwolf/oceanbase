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

#ifndef OCEANBASE_SHARE_TABLE_OB_EXTERNAL_TABLE_ITERATOR_H
#define OCEANBASE_SHARE_TABLE_OB_EXTERNAL_TABLE_ITERATOR_H

#include <stdio.h>
#include <string.h>
#include "common/row/ob_row_iterator.h"
#include "share/ob_i_data_access_service.h"
// #include "share/schema/ob_column_schema.h"
// #include "share/schema/ob_table_schema.h"

namespace oceanbase {
namespace common {
class ObNewRow;
class ObVTableScanParam;
}  // namespace common
namespace share {
namespace schema {
class ObTableSchema;
class ObSchemaGetterGuard;
class ObColumnSchemaV2;
}  // namespace schema
}  // namespace share

namespace sql {
class ObBasicSessionInfo;
}

namespace share {
class ObDatum;
class ObSQLSessionInfo;
class ObLimitParam;

class ObExternalTableIterator : public ObNewRowIterator {
public:
  virtual int get_next_row(ObNewRow*& row) override;
  virtual int get_next_row() override;
  virtual void reset() override;
  virtual int close();
  virtual int inner_close();
  ObExternalTableIterator()
      : fp_(NULL),
        scan_param_(NULL),
        allocator_(NULL),
        session_(NULL),
        scan_cols_schema_(),
        cur_row_(),
        table_schema_(NULL),
        delimiter_(NULL),
        schema_guard_(NULL),
        limit_param_()
  {}

  int open(const char* path);
  int set_table_schema(const share::schema::ObTableSchema* table_schema);
  int set_scan_param(ObVTableScanParam* scan_param);
  inline void set_delimiter(const char* delimiter)
  {
    delimiter_ = delimiter;
  }
  inline void set_schema_guard(share::schema::ObSchemaGetterGuard* schema_guard)
  {
    schema_guard_ = schema_guard;
  }

private:
  int skip_offset();
  virtual int inner_get_next_row(ObNewRow*& row);

  FILE* fp_;
  const ObVTableScanParam* scan_param_;
  ObIAllocator* allocator_;
  sql::ObSQLSessionInfo* session_;
  common::ObSEArray<const share::schema::ObColumnSchemaV2*, 16> scan_cols_schema_;
  common::ObNewRow cur_row_;
  const share::schema::ObTableSchema* table_schema_;
  const char* delimiter_;
  share::schema::ObSchemaGetterGuard* schema_guard_;
  common::ObLimitParam limit_param_;
  const int64_t BUF_SIZE = 1024;
  DISALLOW_COPY_AND_ASSIGN(ObExternalTableIterator);
};
}  // namespace share
}  // namespace oceanbase

#endif