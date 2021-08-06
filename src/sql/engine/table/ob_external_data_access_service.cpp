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

#include "ob_external_data_access_service.h"
#include "share/schema/ob_schema_getter_guard.h"
#include "rootserver/ob_root_service.h"

#define USING_LOG_PREFIX SQL

using namespace oceanbase::common;
using namespace oceanbase::sql;
using namespace oceanbase::share::schema;
using namespace oceanbase::share;
using oceanbase::common::ObNewRowIterator;
using rootserver::ObRootService;

namespace oceanbase {
// namespace share
namespace sql {
int ObExternalDataAccessService::table_scan(ObVTableScanParam& params, ObNewRowIterator*& result)
{
  int ret = OB_SUCCESS;
  const ObTableSchema* table_schema = NULL;
  ObSchemaGetterGuard& schema_guard = params.get_schema_guard();
  ObExternalTableIterator* iter = NULL;
  ObIAllocator& allocator = *params.scan_allocator_;

  LOG_DEBUG("enter ObExternalDataAccessService::table_scan ", K(params));

  if (OB_FAIL(root_service_.get_schema_service().get_schema_guard(schema_guard))) {
    LOG_WARN("get schema guard failed", K(ret));
  } else if (OB_FAIL(schema_guard.get_table_schema(params.pkey_.table_id_, table_schema))) {
    ret = OB_TABLE_NOT_EXIST;
    LOG_WARN("fail to get table schema", K(ret), K(params.pkey_));
  } else if (OB_FAIL(get_iterator(params, table_schema, iter))) {
    LOG_WARN("fail to get iterator", K(ret));
  } else if (OB_FAIL(iter->set_scan_param(&params))) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("fail to set scan param", K(ret), K(params));
  } else if (OB_FAIL(iter->set_table_schema(table_schema))) {
    LOG_WARN("fail to set table schema", K(table_schema));
  } else {
    LOG_DEBUG("external table", K(table_schema->get_external_protocal()), K(table_schema->get_external_format()));
    // iter->set_delimiter(table_schema->get_external_delimiters().ptr());
    if (OB_FAIL(iter->open())) {
      LOG_WARN("fail to open file", K(table_schema->get_external_url()));
    } else {
      result = static_cast<ObNewRowIterator*>(iter);
      LOG_DEBUG("success to set ObExternalTableIterator", K(params));
    }
  }
  if (OB_FAIL(ret)) {
    allocator.free(iter);
  }
  return ret;
}

int ObExternalDataAccessService::get_iterator(
    ObVTableScanParam& params, const ObTableSchema* table_schema, ObExternalTableIterator*& iter)
{
  int ret = OB_SUCCESS;
  void* buf = NULL;
  ObString protocal = table_schema->get_external_protocal();
  ObString format = table_schema->get_external_format();
  ObExternalTableIterator* cur_iter = nullptr;
  ObIExternalLoader* loader = nullptr;
  ObIAllocator* allocator = params.scan_allocator_;
  iter = nullptr;

  // 创建 external loader
  if (protocal == "file") {
    if (OB_ISNULL(buf = static_cast<ObExternalFileLoader*>(allocator->alloc(sizeof(ObExternalFileLoader))))) {
      ret = OB_ALLOCATE_MEMORY_FAILED;
      LOG_ERROR("fail to alloc memory", K(ret));
    } else if (OB_ISNULL(loader = new (buf) ObExternalFileLoader(allocator))) {
      ret = OB_ALLOCATE_MEMORY_FAILED;
      LOG_ERROR("fail to new", K(ret));
    }
  } else {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("wrong protocal type", K(protocal));
  }

  if (format == "csv") {
    if (OB_ISNULL(buf = static_cast<ObExternalCSVIterator*>(allocator->alloc(sizeof(ObExternalCSVIterator))))) {
      ret = OB_ALLOCATE_MEMORY_FAILED;
      LOG_ERROR("fail to alloc memory", K(ret));
    } else if (OB_ISNULL(cur_iter = new (buf) share::ObExternalCSVIterator(loader))) {
      ret = OB_ALLOCATE_MEMORY_FAILED;
      LOG_ERROR("fail to new", K(ret));
    }
  } else {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("wrong format type", K(format));
  }

  if (OB_SUCC(ret)) {
    iter = cur_iter;
  }

  return ret;
}

int ObExternalDataAccessService::revert_scan_iter(ObNewRowIterator* result)
{
  int ret = OB_SUCCESS;
  if (NULL == result) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("invalid argument", K(ret));
  } else {
    ObExternalTableIterator* et_iter = dynamic_cast<ObExternalTableIterator*>(result);
    if (NULL == et_iter) {
      ret = OB_INVALID_ARGUMENT;
      LOG_WARN("dynamic_cast failed, iter is not et iter", K(ret));
    } else if (OB_FAIL(et_iter->close())) {
      LOG_WARN("fail to close ObNewRowIterator", K(ret));
    } else {
      et_iter->~ObExternalTableIterator();
      et_iter = NULL;
    }
  }
  return ret;
}
}  // namespace sql
}  // namespace oceanbase