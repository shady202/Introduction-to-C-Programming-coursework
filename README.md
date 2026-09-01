# Student Management and Activity Tracking System (C)

A role-based console application written in C for managing students, modules, and extra-curricular activities.

This repository is presented as an undergraduate Computer Science portfolio project, with a focus on secure software thinking and core systems programming fundamentals.

## Project Overview

The system supports four user roles:
- **Student**: module/activity registration and progress reporting
- **Administrator**: user account management
- **Programme Coordinator**: module/activity catalogue management
- **Programme Leader**: activity tracking and report generation

Data is persisted in flat text files under `data/`.

## Skills and Concepts Demonstrated

- C programming fundamentals (structs, pointers, arrays, functions)
- File I/O and persistent data handling
- Menu-driven CLI application design
- Role-based access patterns
- Input validation and defensive checks
- Software organization and repository hygiene
- Security awareness (documented risks and mitigation ideas)

## Repository Structure

```text
.
├── src/
│   ├── main.c
│   └── headers/
│       ├── admin.h
│       ├── student.h
│       ├── programme_coordinator.h
│       └── programme_leader.h
├── data/
│   ├── sample_login_data.txt
│   ├── sample_students.txt
│   ├── sample_modules.txt
│   ├── sample_extra_activities.txt
│   └── README_DATA.md
├── docs/
│   ├── ARCHITECTURE.md
│   ├── SECURITY.md
│   └── REQUIREMENTS.md
├── bin/
├── Makefile
├── .gitattributes
├── .gitignore
└── LICENSE
```

## Build and Run

### Prerequisites
- GCC (or compatible C compiler)
- Make

### Commands
```bash
make
make run
make clean
```

## Security Considerations

This is coursework code and not production-ready security software. Key security findings and improvements are documented in [`docs/SECURITY.md`](docs/SECURITY.md), including:
- Plain-text credential storage risk
- Input-handling limitations
- Lack of encryption and audit controls

## Academic Context

This project was developed as part of university C programming coursework and is maintained here as a portfolio artifact to showcase software engineering fundamentals relevant to cyber security pathways.
