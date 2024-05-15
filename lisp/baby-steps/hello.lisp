(defvar *msg* "Kiss my lisp lip")

(defun greeter (name) (format t "Hey mate, how ya doin' ~A?~%" name))

(defvar *pipol* '("Midnight" "Corvus"))

(loop for name in *pipol* do (greeter name))
(dolist (name *pipol*) (greeter name))
