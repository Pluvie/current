bool __map_prebuilt_int32_compare (
    void* k1_address,
    void* k2_address
)
/**
 * This function shall compare two keys and return true if they have the value as
 * `int32`. */
{
  return (*(int32*) k1_address == *(int32*) k2_address);
}
