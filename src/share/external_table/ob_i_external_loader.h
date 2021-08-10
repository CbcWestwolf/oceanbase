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

#ifndef OCEANBASE_SHARE_TABLE_OB_EXTERNAL_LOADER_H
#define OCEANBASE_SHARE_TABLE_OB_EXTERNAL_LOADER_H

namespace oceanbase {
namespace share {
namespace schema {
class ObTableSchema;
}
}  // namespace share
namespace share {

class ObIExternalLoader {
public:
  ObIExternalLoader(ObIAllocator* allocator) : allocator_(allocator)
  {}
  virtual ~ObIExternalLoader()
  {}
  virtual int open(const schema::ObTableSchema* table_schema) = 0;
  virtual int read(char*& buf, long& read_len) = 0;
  virtual bool has_next() = 0;
  virtual int close() = 0;
  virtual void reset() = 0;

protected:
  ObIAllocator* allocator_;
};
}  // namespace share
}  // namespace oceanbase

#endif