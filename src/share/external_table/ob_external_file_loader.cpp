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

#include "ob_external_file_loader.h"

namespace oceanbase {
namespace share {
int ObExternalFileLoader::open(const schema::ObTableSchema* table_schema)
{
  int ret = OB_SUCCESS;
  const char* path = table_schema->get_external_url().ptr();

  if (OB_ISNULL(fp_ = fopen(path, "r"))) {
    ret = OB_FILE_NOT_EXIST;
    LOG_WARN("external path not exist", K(path), K(ret));
  }

  return ret;
}

int ObExternalFileLoader::read(union DataSource& data_source)
{
  int ret = OB_SUCCESS;
  char* cur_buf = nullptr;
  if (OB_ISNULL(fp_)) {
    ret = OB_FILE_NOT_OPENED;
    LOG_WARN("file not open", K(ret), K(fp_));
  } else if (feof(fp_)) {
    ret = OB_ITER_END;
  } else if (OB_FAIL(fseek(fp_, 0L, SEEK_END))) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("fail to locate to the end of file", K(ret));
  } else if (OB_UNLIKELY(-1 == (data_source.buffer.buf_size_ = ftell(fp_)))) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("fail to get the length of the file", K(ret));
  } else if (OB_ISNULL(
                 cur_buf = static_cast<char*>(allocator_->alloc(sizeof(char) * (data_source.buffer.buf_size_ + 1))))) {
    ret = OB_ALLOCATE_MEMORY_FAILED;
    LOG_WARN("fail to alloc new obj", K(ret));
  } else if (OB_FAIL(fseek(fp_, 0L, SEEK_SET))) {
    ret = OB_ERR_UNEXPECTED;
    allocator_->free(cur_buf);
    LOG_WARN("fail to locate to the begin of file", K(ret));
  } else if (OB_UNLIKELY(0 == (data_source.buffer.buf_size_ =
                                      fread(cur_buf, sizeof(char), data_source.buffer.buf_size_, fp_)))) {
    ret = OB_ERR_UNEXPECTED;
    allocator_->free(cur_buf);
    LOG_WARN("fail to fread the file", K(ret), K(ferror(fp_)));
  } else {
    cur_buf[data_source.buffer.buf_size_] = '\0';
    data_source.buffer.ptr_ = cur_buf;
  }

  return ret;
}

int ObExternalFileLoader::close()
{
  int ret = OB_SUCCESS;
  if (OB_ISNULL(fp_)) {
    ret = OB_FILE_NOT_OPENED;
    LOG_WARN("try to close a closed file");
  } else if (OB_FAIL(fclose(fp_))) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("fail to close file", K(fp_));
  } else {
    LOG_DEBUG("succ to close file", K(fp_));
  }
  return ret;
}

void ObExternalFileLoader::reset()
{
  fp_ = NULL;
  allocator_ = NULL;
}

}  // namespace share
}  // namespace oceanbase