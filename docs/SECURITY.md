# Security Review (Coursework Baseline)

## Scope
Assessment of current repository code and data-handling approach for portfolio transparency.

## Findings

1. **Plain-text passwords in data files**  
   - Risk: credential exposure if repository is shared publicly.
   - Improvement: hash passwords with salt (e.g., bcrypt/Argon2 in future refactor).

2. **No transport/storage encryption**  
   - Risk: local file disclosure and tampering.
   - Improvement: protect sensitive data paths, encrypt at rest where appropriate.

3. **Input handling relies on scanf in multiple paths**  
   - Risk: malformed input and buffer-handling weaknesses.
   - Improvement: migrate sensitive input paths to bounded `fgets` + validation parsing.

4. **No audit logging or lockout policy**  
   - Risk: limited forensic visibility and brute-force resistance.
   - Improvement: add login attempt tracking, lockout thresholds, and audit events.

## Portfolio Note
This project is intentionally preserved near its coursework baseline and documented with security limitations to demonstrate analytical maturity and secure development awareness.
