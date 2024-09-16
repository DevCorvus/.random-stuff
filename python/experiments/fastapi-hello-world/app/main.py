from fastapi import FastAPI

from .features.users.router import router as user_router
from .database import engine
from . import models

models.Base.metadata.create_all(bind=engine)


app = FastAPI()

app.include_router(user_router)


@app.get("/")
async def home():
    return "Hello World"
