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

#ifndef OCEANBASE_SHARE_TABLE_OB_EXTERNAL_TOK_ITERATOR_H
#define OCEANBASE_SHARE_TABLE_OB_EXTERNAL_TOK_ITERATOR_H

#include "ob_external_table_iterator.h"
#include "ob_i_external_loader.h"

namespace oceanbase {

namespace common {
class ObNewRow;
class ObVTableScanParam;
class ObLimitParam;
}  // namespace common

namespace sql {
class ObSQLSessionInfo;
}
namespace share {
namespace schema {
class ObTableSchema;
}
}  // namespace share

namespace share {

class ObExternalTokenIterator : public ObExternalTableIterator {
public:
  ObExternalTokenIterator(ObIExternalLoader* external_loader)
      : ObExternalTableIterator(external_loader), tokens_(nullptr), field_delimiter_(",")
  {
    data_source_.buffer.ptr_ = nullptr;
    data_source_.buffer.buf_size_ = 0L;
  }
  virtual int inner_get_next_row(ObNewRow*& row) override;
  virtual int set_table_schema(const schema::ObTableSchema* table_schema) override;
  virtual void reset() override;

private:
  const int BUFFER_SIZE = 1024;
  char* tokens_;
  ObString field_delimiter_;
};

}  // namespace share
}  // namespace oceanbase
#endif