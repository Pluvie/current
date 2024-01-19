uint64 __map_prebuilt_int32_hash (
    void* key
)
/**
 * This function returns an identity hash value. */
{
  return (uint64) *((int32*) key);
}
