#!/usr/bin/env bash

psql -c "
drop table if exists test;
drop extension if exists suuid;
create extension suuid;
begin;
create table test(id suuid, name text);
insert into test(name) values ('hello');
commit;"