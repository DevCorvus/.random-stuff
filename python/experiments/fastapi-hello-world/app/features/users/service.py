from sqlalchemy.orm import Session
from app.features.password.service import encrypt_password

from app.models import User
from app.schemas import UserCreate


def create_user(db: Session, data: UserCreate):
    hashed_password = encrypt_password(data.password)

    new_user = User(
        firstname=data.firstname,
        lastname=data.lastname,
        email=data.email,
        password=hashed_password,
    )

    db.add(new_user)
    db.commit()

    return new_user


def get_user_by_email(db: Session, email: str):
    return db.query(User).filter(User.email == email).first()
