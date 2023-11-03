void user_print (
    struct user user
)
{
  fprintf(stderr, "{%i, %i, %s}", user.id, user.age, user.name);
}
