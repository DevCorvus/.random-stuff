import { DatabaseInterface } from '../../database/types';

export interface Product {
    id: string;
    title: string;
    description: string;
    price: number;
    stock: number;
    createdAt: Date;
    updatedAt: Date;
}

export interface AddProductInterface {
    title: string;
    description: string;
    price: number;
    stock: number;
}

interface ProductRepositoryInterface {
    add(data: AddProductInterface): Promise<Product>;
    findById(id: string): Promise<Product | null>;
    reset(): Promise<void>;
}

export class ProductRepository implements ProductRepositoryInterface {
    constructor(private db: DatabaseInterface) {}

    async add(data: AddProductInterface): Promise<Product> {
        const query =
            'INSERT INTO products(title, description, price, stock) VALUES($1, $2, $3, $4) RETURNING *';
        const values = [data.title, data.description, data.price, data.stock];

        const result = await this.db.query(query, values);

        const product = result.rows[0];

        return this.format(product);
    }

    async findById(id: string): Promise<Product | null> {
        const query =
            'SELECT id, title, description, price, stock ,created_at, updated_at FROM products WHERE id = $1';
        const values = [id];

        const result = await this.db.query(query, values);

        if (result.rowCount === 0) {
            return null;
        }

        const product = result.rows[0];

        return this.format(product);
    }

    async reset(): Promise<void> {
        await this.db.query('DELETE FROM products');
    }

    private format(data: any): Product {
        return {
            id: data.id,
            title: data.title,
            description: data.description,
            price: data.price,
            stock: data.stock,
            createdAt: data.created_at,
            updatedAt: data.updated_at,
        };
    }
}
