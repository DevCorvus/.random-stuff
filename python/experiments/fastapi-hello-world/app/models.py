from sqlalchemy import Boolean, Column, DateTime, String
from sqlalchemy.sql import func
from uuid import uuid4

from .database import Base


class User(Base):
    __tablename__ = "users"

    id = Column(String(36), primary_key=True, default=str(uuid4()))
    email = Column(String, unique=True, index=True)
    password = Column(String)
    firstname = Column(String)
    lastname = Column(String)
    is_active = Column(Boolean, default=True)
    created_at = Column(DateTime(timezone=True), default=func.now())
    updated_at = Column(
        DateTime(timezone=True), default=func.now(), onupdate=func.now()
    )
