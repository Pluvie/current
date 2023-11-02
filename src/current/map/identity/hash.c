/**
 * This function returns an identity hash value. */
uint32 __map_identity_hash (
    void* key
)
{
  return (uint32) *((int*) key);
}
