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
void ObExternalOSSLoader::init_options()
{
  oss_client_options_->config = oss_config_create(oss_client_options_->pool);
  /* 用char*类型的字符串初始化aos_string_t类型。*/
  aos_str_set(&oss_client_options_->config->endpoint, ENDPOINT);
  aos_str_set(&oss_client_options_->config->access_key_id, ACCESS_KEY_ID);
  aos_str_set(&oss_client_options_->config->access_key_secret, ACCESS_KEY_SECRET);
  /* 是否使用了CNAME。0表示不使用。*/
  oss_client_options_->config->is_cname = 0;
  /* 用于设置网络相关参数，比如超时时间等。*/
  oss_client_options_->ctl = aos_http_controller_create(oss_client_options_->pool, 0);
}

void ObExternalOSSLoader::parse_url()
{
  // TODO
}

int ObExternalOSSLoader::open(const schema::ObTableSchema* table_schema)
{
  int ret = OB_SUCCESS;

  /* 在程序入口调用aos_http_io_initialize方法来初始化网络、内存等全局资源。*/
  if (aos_http_io_initialize(NULL, 0) != AOSE_OK) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("aos_http_io_initialize fail");
  }

  /* 重新创建一个内存池，第二个参数是NULL，表示没有继承其它内存池。*/
  aos_pool_create(&pool_, NULL);
  /* 初始化options，该参数包括endpoint、access_key_id、acces_key_secret、is_cname、curl等全局配置信息。*/
  /* 在内存池中分配内存给options。*/
  oss_client_options_ = oss_request_options_create(pool_);
  /* 初始化Client的选项oss_client_options。*/
  init_options();
  has_read_ = false;
  new (&location_) ObString(table_schema->get_external_url());

  return ret;
}

int ObExternalOSSLoader::read(union DataSource& data_source)
{
  int ret = OB_SUCCESS;

  /* 初始化参数。*/
  aos_string_t bucket;
  aos_string_t object;
  aos_buf_t* content = NULL;
  aos_table_t* params = NULL;
  aos_table_t* headers = NULL;
  aos_table_t* resp_headers = NULL;
  aos_status_t* resp_status = NULL;
  int64_t size = 0;
  int64_t pos = 0;
  char* cur_buf = nullptr;
  aos_str_set(&bucket, BUCKET_NAME);
  aos_str_set(&object, location_.ptr());
  aos_list_init(&buffer_);

  resp_status =
      oss_get_object_to_buffer(oss_client_options_, &bucket, &object, headers, params, &buffer_, &resp_headers);
  data_source.buffer.ptr_ = nullptr;

  if (aos_status_is_ok(resp_status)) {
    data_source.buffer.buf_size_ = aos_buf_list_len(&buffer_);
    cur_buf = static_cast<char*>(allocator_->alloc(sizeof(char) * (data_source.buffer.buf_size_ + 1)));
    cur_buf[data_source.buffer.buf_size_] = '\0';
    aos_list_for_each_entry(aos_buf_t, content, &buffer_, node)
    {
      size = aos_buf_size(content);
      memcpy(cur_buf + pos, content->pos, size);
      pos += size;
    }
    has_read_ = true;
    data_source.buffer.ptr_ = cur_buf;
  } else {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("fail to read oss", K(ret), K(resp_status));
  }
  /* 释放内存池，相当于释放了请求过程中各资源分配的内存。*/
  aos_pool_destroy(pool_);
  /* 释放之前分配的全局资源。*/
  aos_http_io_deinitialize();

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