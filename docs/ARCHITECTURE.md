# Architecture

## High-Level Components

```text
+-----------------------+
| Authentication/Login  |
| (admin.h functions)   |
+-----------+-----------+
            |
            v
+-----------------------+
| Role Router (main.c)  |
+-----+--------+--------+
      |        |        |
      v        v        v
  Student   Admin   Coordinator/Leader
  Menu      Menu    Menus
      \        |        /
       \       |       /
        v      v      v
      Text-file persistence
      (data/sample_*.txt)
```

## Data Flow Summary

1. Login data is read from `data/sample_login_data.txt`.
2. User role is identified and routed to the matching menu.
3. Each role reads/writes the relevant sample data files.
4. Updates are persisted to text files for later sessions.
