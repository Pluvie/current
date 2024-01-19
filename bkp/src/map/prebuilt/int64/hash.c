uint64 __map_prebuilt_int64_hash (
    void* key
)
/**
 * This function returns an identity hash value. */
{
  return (uint64) *((int64*) key);
}
