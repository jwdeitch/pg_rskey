CREATE TYPE rskey;

CREATE FUNCTION rskey_in(cstring)
  RETURNS rskey
AS '$libdir/rskey'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION rskey_out(rskey)
  RETURNS cstring
AS '$libdir/rskey'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION rskey_recv(internal)
  RETURNS rskey
AS '$libdir/rskey'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION rskey_send(rskey)
  RETURNS bytea
AS '$libdir/rskey'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE rskey (
  internallength = VARIABLE,
  input = rskey_in,
  output = rskey_out,
  receive = rskey_recv,
  send = rskey_send,
  alignment = 4
);