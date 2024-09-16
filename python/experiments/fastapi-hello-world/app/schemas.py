from datetime import datetime
from pydantic import BaseModel


class UserBase(BaseModel):
    firstname: str
    lastname: str
    email: str


class UserCreate(UserBase):
    password: str


class User(UserBase):
    id: str
    is_active: bool
    created_at: datetime
    updated_at: datetime


class UserLogin(BaseModel):
    email: str
    password: str
