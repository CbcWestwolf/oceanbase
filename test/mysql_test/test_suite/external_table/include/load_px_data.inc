set ob_query_timeout=1000000000;
--disable_warnings
drop database if exists et_test;
--enable_warnings
create database et_test;
use et_test;

# # 关闭 recyclebin
set recyclebin = 0;

# 场景：一个年级 6 个班，修了2门课，英语和数学

create external table file_stu (
  sid     int,
  name    varchar(32),
  cls     int
) external_url='/home/chenbochuan.cbc/data/px/stu.dat';

create external table file_teacher (
  tid        int,
  name       varchar(32),
  subject    varchar(4)
) external_url='/home/chenbochuan.cbc/data/px/teacher.dat';

create external table file_score (
  sid     int,
  subject varchar(4),
  score   int
) external_url='/home/chenbochuan.cbc/data/px/score.dat';

create external table oss_stu (
  sid     int,
  name    varchar(32),
  cls     int
) external_url='px/stu.dat', external_protocal='oss';

create external table oss_teacher (
  tid        int,
  name       varchar(32),
  subject    varchar(4)
) external_url='px/teacher.dat', external_protocal='oss';

create external table oss_score (
  sid     int,
  subject varchar(4),
  score   int
) external_url='px/score.dat', external_protocal='oss';