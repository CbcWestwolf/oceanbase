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

#include "ob_external_oss_loader.h"

namespace oceanbase {
namespace share {

int ObExternalOSSLoader::open(const schema::ObTableSchema* table_schema)
{
  int ret = OB_SUCCESS;

  has_read_ = false;

  new (&access_info_) ObString(table_schema->get_external_url());
  file_name_ = access_info_.split_on('?');
  oss_reader_.open(file_name_, access_info_);
  file_size_ = oss_reader_.get_length();

  return ret;
}

int ObExternalOSSLoader::read(union DataSource& data_source)
{
  int ret = OB_SUCCESS;

  if (!has_read_) {

    char* cur_buf = nullptr;
    cur_buf = static_cast<char*>(allocator_->alloc(sizeof(char) * (file_size_ + 1)));
    oss_reader_.pread(cur_buf, file_size_, 0, file_size_);
    has_read_ = true;
    cur_buf[file_size_] = '\0';
    data_source.buffer.ptr_ = cur_buf;
    data_source.buffer.buf_size_ = file_size_;
  }

  return ret;
}

int ObExternalOSSLoader::close()
{
  int ret = OB_SUCCESS;

  return ret;
}

void ObExternalOSSLoader::reset()
{
  has_read_ = false;
}
}  // namespace share
}  // namespace oceanbase