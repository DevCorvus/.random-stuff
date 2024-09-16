import bcrypt

PASSWORD_ENCODING = "utf-8"


def encrypt_password(password: str) -> str:
    salt = bcrypt.gensalt()
    password_bytes = bytes(password, PASSWORD_ENCODING)
    hashed_password = bcrypt.hashpw(password_bytes, salt)

    return hashed_password.decode(PASSWORD_ENCODING)


def compare_password(password: str, hashed_password: str) -> bool:
    password_bytes = bytes(password, PASSWORD_ENCODING)
    hashed_password_bytes = bytes(hashed_password, PASSWORD_ENCODING)

    return bcrypt.checkpw(password_bytes, hashed_password_bytes)
