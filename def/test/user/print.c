void user_print (
    struct user user
)
{
  fprintf(stderr, "{%i, %i, %s}", user.id, user.age, user.name);
}

void user_ptr_print (
    struct user* user
)
{
  if (user == NULL)
    fprintf(stderr, "-");
  else
    fprintf(stderr, "{%i, %i, %s}", user->id, user->age, user->name);
}
