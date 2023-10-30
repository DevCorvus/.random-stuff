package routes

import (
	"fiber-jwt-auth/controller"

	"github.com/gofiber/fiber/v2"
)

func Setup(app *fiber.App) {
	router := app.Group("/api")

	router.Post("/register", controller.Register)
	router.Post("/login", controller.Login)
	router.Get("/account", controller.User)
	router.Post("/logout", controller.Logout)
}
