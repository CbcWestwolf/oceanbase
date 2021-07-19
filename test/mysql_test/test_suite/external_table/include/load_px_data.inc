set ob_query_timeout=1000000000;
--disable_warnings
drop database if exists et_test;
--enable_warnings
create database et_test;
use et_test;

# # 关闭 recyclebin
set recyclebin = 0;

# 场景：一个年级 6 个班，修了2门课，英语和数学

create external table file_csv_stu (
  sid     int,
  name    varchar(32),
  cls     int
) external_url='/home/chenbochuan.cbc/data/px/stu.csv';

create external table file_csv_teacher (
  tid        int,
  name       varchar(32),
  subject    varchar(4)
) external_url='/home/chenbochuan.cbc/data/px/teacher.csv';

create external table file_csv_score (
  sid     int,
  subject varchar(4),
  score   int
) external_url='/home/chenbochuan.cbc/data/px/score.csv';

create external table oss_csv_stu (
  sid     int,
  name    varchar(32),
  cls     int
) external_url='oss://external-table/px/stu.csv?host=oss-cn-hangzhou.aliyuncs.com&access_id=DEscLTAIStR9ccJJGQFHEaP2&access_key=bhdegy7AqfsFLj]2YpolgMjyTFVZNhK', external_protocal='oss';

create external table oss_csv_teacher (
  tid        int,
  name       varchar(32),
  subject    varchar(4)
) external_url='oss://external-table/px/teacher.csv?host=oss-cn-hangzhou.aliyuncs.com&access_id=DEscLTAIStR9ccJJGQFHEaP2&access_key=bhdegy7AqfsFLj]2YpolgMjyTFVZNhK', external_protocal='oss';

create external table oss_csv_score (
  sid     int,
  subject varchar(4),
  score   int
) external_url='oss://external-table/px/score.csv?host=oss-cn-hangzhou.aliyuncs.com&access_id=DEscLTAIStR9ccJJGQFHEaP2&access_key=bhdegy7AqfsFLj]2YpolgMjyTFVZNhK', external_protocal='oss';

create external table file_tok_stu (
  sid     int,
  name    varchar(32),
  cls     int
) external_url='/home/chenbochuan.cbc/data/px/stu.tok', external_format='tok';

create external table file_tok_teacher (
  tid        int,
  name       varchar(32),
  subject    varchar(4)
) external_url='/home/chenbochuan.cbc/data/px/teacher.tok', external_format='tok';

create external table file_tok_score (
  sid     int,
  subject varchar(4),
  score   int
) external_url='/home/chenbochuan.cbc/data/px/score.tok', external_format='tok';

create external table oss_tok_stu (
  sid     int,
  name    varchar(32),
  cls     int
) external_url='oss://external-table/px/stu.tok?host=oss-cn-hangzhou.aliyuncs.com&access_id=DEscLTAIStR9ccJJGQFHEaP2&access_key=bhdegy7AqfsFLj]2YpolgMjyTFVZNhK', external_protocal='oss', external_format='tok';

create external table oss_tok_teacher (
  tid        int,
  name       varchar(32),
  subject    varchar(4)
) external_url='oss://external-table/px/teacher.tok?host=oss-cn-hangzhou.aliyuncs.com&access_id=DEscLTAIStR9ccJJGQFHEaP2&access_key=bhdegy7AqfsFLj]2YpolgMjyTFVZNhK', external_protocal='oss', external_format='tok';

create external table oss_tok_score (
  sid     int,
  subject varchar(4),
  score   int
) external_url='oss://external-table/px/score.tok?host=oss-cn-hangzhou.aliyuncs.com&access_id=DEscLTAIStR9ccJJGQFHEaP2&access_key=bhdegy7AqfsFLj]2YpolgMjyTFVZNhK', external_protocal='oss', external_format='tok';
