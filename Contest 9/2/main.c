extern void normalize_path(char* path)
{
    const int next = 1;
    const int next_next = 2;
    int i = 0;
    char dot = '.';
    char end = '\n';
    char null = '\0';
    char root = '/';

    do {
        if (end == *(path + i))
            break;

        if (null == *(path + i))
            break;

        if (root == *(path + i)) {
            while (root == *(path + i + next))
                ++i;
        }

        if (dot == *(path + i)) { // .

            if (dot == *(path + i + next) &&
                root == *(path + i + next_next)) { // ./
                i += next_next;
                path -= next_next;
                do {
                    --path;
                    ++i;
                } while (*path != root);
                i += next_next;
            }

            if (root == *(path + i + next)) { // /
                i += next_next;
            }
        }

        *path = *(path + i);
        ++path;
    } while (next);

    *path = null;
    for (; *(path - next) > 0; --path) {}
}
