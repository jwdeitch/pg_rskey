CREATE TYPE suuid;

CREATE SEQUENCE suuid_sequence;

CREATE FUNCTION suuid_in(cstring)
  RETURNS suuid
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION suuid_out(suuid)
  RETURNS cstring
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION id_encode()
RETURNS text
AS '$libdir/suuid'
LANGUAGE C;

CREATE TYPE suuid (
  internallength = VARIABLE,
  input = suuid_in,
  output = suuid_out,
  alignment = double,
  default = id_encode
);