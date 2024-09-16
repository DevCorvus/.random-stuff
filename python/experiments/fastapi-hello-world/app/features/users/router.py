from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.orm import Session

from app.features.password.service import compare_password

from . import service
from app.schemas import UserCreate, User, UserLogin
from app.dependencies import get_db


router = APIRouter(tags=["users"])


@router.post("/signup", response_model=User, status_code=201)
async def signup(user: UserCreate, db: Session = Depends(get_db)):
    try:
        new_user = service.create_user(db, user)
        return new_user
    except:
        raise HTTPException(
            status_code=status.HTTP_409_CONFLICT, detail="Email already in use"
        )


@router.post("/login", status_code=201)
async def login(credentials: UserLogin, db: Session = Depends(get_db)):
    user = service.get_user_by_email(db, credentials.email)

    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND)

    do_passwords_match = compare_password(credentials.password, str(user.password))

    if not do_passwords_match:
        raise HTTPException(status_code=status.HTTP_403_FORBIDDEN)

    return "Logged In"
