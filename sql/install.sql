CREATE TYPE suuid;

CREATE FUNCTION suuid_in(cstring)
  RETURNS suuid
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION suuid_out(suuid)
  RETURNS cstring
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION suuid_recv(internal)
  RETURNS suuid
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION suuid_send(suuid)
  RETURNS bytea
AS '$libdir/suuid'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE suuid (
  internallength = VARIABLE,
  input = suuid_in,
  output = suuid_out,
  receive = suuid_recv,
  send = suuid_send,
  alignment = 4
);