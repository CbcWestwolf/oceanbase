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

#ifndef OCEANBASE_OB_EXTERNAL_DATA_ACCESS_SERVICE_H
#define OCEANBASE_OB_EXTERNAL_DATA_ACCESS_SERVICE_H

#include "share/external_table/ob_external_table_iterator.h"
#include "share/external_table/ob_i_external_loader.h"
#include "share/external_table/ob_external_file_loader.h"
#include "share/external_table/ob_external_oss_loader.h"
#include "share/external_table/ob_external_csv_iterator.h"

namespace oceanbase {
namespace common {
class ObAddr;
class ObServerConfig;
class ObVTableScanParam;
class ObIDataAccessService;
class ObNewRowIterator;
}  // namespace common

namespace share {
class ObExternalFileLoader;
class ObExternalCSVIterator;
class ObExternalOSSLoader;
class ObExternalTableIterator;
}  // namespace share

namespace share {
namespace schema {

class ObTableSchema;
}  // namespace schema
}  // namespace share

namespace storage {
class ObTableScanParam;
}

namespace rootserver {
class ObRootService;
}

namespace sql {

class ObExternalDataAccessService : public common::ObIDataAccessService {
public:
  ObExternalDataAccessService(
      rootserver::ObRootService& root_service, common::ObAddr& addr, common::ObServerConfig* config)
      : root_service_(root_service), addr_(addr), config_(config)
  {}
  virtual ~ObExternalDataAccessService()
  {}

  virtual int table_scan(common::ObVTableScanParam& param, common::ObNewRowIterator*& result);
  virtual int revert_scan_iter(common::ObNewRowIterator* iter);

  virtual int join_mv_scan(storage::ObTableScanParam&, storage::ObTableScanParam&, common::ObNewRowIterator*&)
  {
    int ret = common::OB_NOT_SUPPORTED;
    COMMON_LOG(WARN, "external data access not support join mv scan interface", K(ret));
    return ret;
  }

private:
  int get_iterator(ObVTableScanParam& params, const share::schema::ObTableSchema* table_schema,
      share::ObExternalTableIterator*& iter);

  rootserver::ObRootService& root_service_;
  common::ObAddr& addr_;
  common::ObServerConfig* config_;
  DISALLOW_COPY_AND_ASSIGN(ObExternalDataAccessService);
};
}  // namespace sql
}  // namespace oceanbase
#endif  // OCEANBASE_OB_EXTERNAL_DATA_ACCESS_SERVICE_H