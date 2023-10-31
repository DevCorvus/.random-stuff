import { DatabaseInterface } from '../../../database/types';

export interface ProductImage {
    id: string;
    productId: string;
    path: string;
    type: string;
    createdAt: Date;
}

export interface AddProductImageInterface {
    productId: string;
    path: string;
    type: string;
}

interface ProductImageRepositoryInterface {
    add(data: AddProductImageInterface): Promise<ProductImage>;
    reset(): Promise<void>;
}

export class ProductImageRepository implements ProductImageRepositoryInterface {
    constructor(private db: DatabaseInterface) {}

    async add(data: AddProductImageInterface): Promise<ProductImage> {
        const query =
            'INSERT INTO product_images(product_id, path, type) VALUES($1, $2, $3) RETURNING *';
        const values = [data.productId, data.path, data.type];

        const result = await this.db.query(query, values);

        const productImage = result.rows[0];

        return {
            id: productImage.id,
            productId: productImage.product_id,
            path: productImage.path,
            type: productImage.type,
            createdAt: productImage.created_at,
        };
    }

    async reset(): Promise<void> {
        await this.db.query('DELETE FROM product_images');
    }
}
