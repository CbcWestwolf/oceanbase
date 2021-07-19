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

#ifndef OCEANBASE_SHARE_TABLE_OB_EXTERNAL_OSS_LOADER_H
#define OCEANBASE_SHARE_TABLE_OB_EXTERNAL_OSS_LOADER_H

#include "ob_i_external_loader.h"

namespace oceanbase {
namespace share {
namespace schema {
class ObTableSchema;
}
}  // namespace share

namespace share {

class ObExternalOSSLoader : public ObIExternalLoader {
public:
  ObExternalOSSLoader(ObIAllocator* allocator) : ObIExternalLoader(allocator), file_size_(-1), has_read_(false)
  {}
  virtual int open(const schema::ObTableSchema* table_schema) override;
  virtual int read(union DataSource& data_source) override;
  inline bool has_next() override
  {
    return !has_read_;
  }
  virtual int close() override;
  virtual void reset() override;

private:
  ObStorageOssReader oss_reader_;
  ObString file_name_;
  ObString access_info_;
  int64_t file_size_;
  bool has_read_;
};

}  // namespace share
}  // namespace oceanbase

#endif