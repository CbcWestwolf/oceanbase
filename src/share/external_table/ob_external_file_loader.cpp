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

#include <string.h>
#include "ob_external_file_loader.h"

namespace oceanbase {
namespace share {
int ObExternalFileLoader::open(const schema::ObTableSchema* table_schema)
{
  int ret = OB_SUCCESS;

  has_read_ = false;

  new (&file_name_) ObString(table_schema->get_external_url());

  if (OB_FAIL(file_reader_.open(file_name_, false))) {
    LOG_WARN("fail to open file reader", K(file_name_), K(ret));
  } else {
    file_size_ = get_file_size(file_name_.ptr());
  }

  return ret;
}

int ObExternalFileLoader::read(union DataSource& data_source)
{
  int ret = OB_SUCCESS;

  if (!has_read_) {
    char* cur_buf = nullptr;
    cur_buf = static_cast<char*>(allocator_->alloc(sizeof(char) * (file_size_ + 1)));
    file_reader_.pread(cur_buf, file_size_, 0, file_size_);
    has_read_ = true;
    cur_buf[file_size_] = '\0';
    if (cur_buf[file_size_ - 1] == '\n') {
      file_size_--;
      cur_buf[file_size_] = '\0';
    }
    data_source.buffer.ptr_ = cur_buf;
    data_source.buffer.buf_size_ = file_size_;
  }

  return ret;
}

int ObExternalFileLoader::close()
{
  int ret = OB_SUCCESS;
  if (file_reader_.is_opened()) {
    file_reader_.close();
  }
  return ret;
}

void ObExternalFileLoader::reset()
{
  has_read_ = false;
}

}  // namespace share
}  // namespace oceanbase