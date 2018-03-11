CREATE TYPE suuid;

CREATE SEQUENCE global_suuid_sequence;

CREATE FUNCTION suuid_in(cstring)
  RETURNS suuid
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION suuid_out(suuid)
  RETURNS cstring
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION new_suuid()
RETURNS text
AS '$libdir/suuid'
LANGUAGE C VOLATILE STRICT;

CREATE TYPE suuid (
  internallength = VARIABLE,
  input = suuid_in,
  output = suuid_out,
  alignment = double,
  default = new_suuid,
  STORAGE = PLAIN
);