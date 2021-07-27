# 0. create table

use test;
CREATE EXTERNAL TABLE IF NOT EXISTS ext (employee_id int, first_name varchar(20), last_name varchar(20), job_id varchar(10), manager_id int, hire_date DATE, salary float, commission_pct float, department_id int, email varchar(25) );