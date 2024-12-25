package stack

type Stack[T any] struct {
	items []T
}

func (t *Stack[T]) IsEmpty() bool {
	return len(t.items) == 0
}

func (t *Stack[T]) Push(value T) {
	t.items = append(t.items, value)
}

func (t *Stack[T]) Pop() *T {
	if t.IsEmpty() {
		return nil
	}

	lastValue := t.items[len(t.items)-1]

	t.items = t.items[:len(t.items)-1]

	return &lastValue
}
