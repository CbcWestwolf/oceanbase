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

#include <linux/limits.h>
#include <apr-1/apr_portable.h>
#include <oss_c_sdk/oss_api.h>
#include <oss_c_sdk/aos_http_io.h>

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
  ObExternalOSSLoader(ObIAllocator* allocator)
      : ObIExternalLoader(allocator), location_(nullptr), has_read_(false), oss_client_options_(nullptr)
  {}
  virtual int open(const schema::ObTableSchema* table_schema) override;
  virtual int read(char*& buf, long& read_len) override;
  inline bool has_next() override
  {
    return !has_read_;
  }
  virtual int close() override;
  virtual void reset() override;

private:
  void parse_url();
  void init_options();

  const char* ENDPOINT = "oss-cn-hangzhou.aliyuncs.com";
  const char* ACCESS_KEY_ID = "";
  const char* ACCESS_KEY_SECRET = "";
  const char* BUCKET_NAME = "external-table";
  ObString location_;
  bool has_read_;
  aos_list_t buffer_;
  oss_request_options_t* oss_client_options_;
  aos_pool_t* pool_; /* 用于内存管理的内存池（pool），等价于apr_pool_t。其实现代码在apr库中。*/
};

}  // namespace share
}  // namespace oceanbase

#endif