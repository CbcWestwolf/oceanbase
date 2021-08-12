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

#include <string.h>
#include "common/row/ob_row_iterator.h"
#include "share/ob_i_data_access_service.h"
#include "ob_i_external_loader.h"

namespace oceanbase {
namespace common {
class ObNewRow;
class ObVTableScanParam;
}  // namespace common
namespace share {
namespace schema {
class ObTableSchema;
class ObColumnSchemaV2;
}  // namespace schema
}  // namespace share

namespace share {
class ObIExternalLoader;

union DataSource {
  DataSource()
  {}
  struct {
    char* ptr_;
    long buf_size_;
  } buffer;
  void* other_handler_;
};

class ObExternalTableIterator : public ObNewRowIterator {
public:
  ObExternalTableIterator(ObIExternalLoader* external_loader)
      : external_loader_(external_loader),
        table_schema_(NULL),
        data_source_(),
        scan_param_(NULL),
        allocator_(NULL),
        scan_cols_schema_(),
        cur_row_()
  {}

  virtual ~ObExternalTableIterator()
  {}

  int open();
  virtual void reset();
  virtual int close();
  virtual int inner_close();
  virtual int get_next_row(ObNewRow*& row) override;
  virtual int get_next_row() override;

  virtual int set_table_schema(const share::schema::ObTableSchema* table_schema);
  virtual int set_scan_param(ObVTableScanParam* scan_param);

protected:
  virtual int inner_get_next_row(ObNewRow*& row) = 0;

  ObIExternalLoader* external_loader_;
  const share::schema::ObTableSchema* table_schema_;
  union DataSource data_source_;
  const ObVTableScanParam* scan_param_;
  ObIAllocator* allocator_;
  common::ObSEArray<const share::schema::ObColumnSchemaV2*, 16> scan_cols_schema_;
  common::ObNewRow cur_row_;

  DISALLOW_COPY_AND_ASSIGN(ObExternalTableIterator);
};
}  // namespace share
}  // namespace oceanbase

#endif