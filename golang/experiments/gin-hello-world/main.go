package main

import (
	"gin-hello-world/handlers"

	"github.com/gin-gonic/gin"
)

// func main() {
// 	r := gin.Default()
// 	r.GET("/ping", func(c *gin.Context) {
// 		c.JSON(200, gin.H{
// 			"message": "pong",
// 		})
// 	})
// 	r.Run() // listen and serve on 0.0.0.0:8080
// }

func main() {
	router := gin.Default()
	router.GET("/books", handlers.GetBooks)
	router.GET("/books/:id", handlers.GetBook)
	router.POST("/books", handlers.AddBook)
	router.PUT("/books/checkout", handlers.CheckoutBook)
	router.PUT("/books/return", handlers.ReturnBook)
	router.Run(":3000")
}
