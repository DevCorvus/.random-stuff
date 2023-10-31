import { UnitOfWork } from '../../database/uow';
import { Category } from '../category/category.repository';
import { ProductImage } from './images/product-image.repository';

export interface ProductWithImagesAndCategories {
    id: string;
    title: string;
    description: string;
    price: number;
    stock: number;
    createdAt: Date;
    updatedAt: Date;
    images: ProductImage[];
    categories: Category[];
}

export interface CreateUpdateProductInterface {
    title: string;
    description: string;
    price: number;
    stock: number;
    images: { path: string; type: string }[];
    categories: { title: string; description: string }[];
}

interface ProductServiceInterface {
    create(
        data: CreateUpdateProductInterface
    ): Promise<ProductWithImagesAndCategories | null>;
    findById(id: string): Promise<ProductWithImagesAndCategories | null>;
    update(id: string, data: CreateUpdateProductInterface): Promise<void>;
    delete(id: string): Promise<void>;
}

export class ProductService implements ProductServiceInterface {
    constructor(private uow: UnitOfWork) {}

    async create(
        data: CreateUpdateProductInterface
    ): Promise<ProductWithImagesAndCategories | null> {
        let productWithImagesAndCategories: ProductWithImagesAndCategories;

        const created = await this.uow.transaction(async (repo) => {
            const product = await repo.product.add(data);

            const images: ProductImage[] = [];

            data.images.forEach(async (img) => {
                const productImage = await repo.productImage.add({
                    productId: product.id,
                    ...img,
                });
                images.push(productImage);
            });

            const categories: Category[] = [];
            data.categories.forEach(async (c) => {
                const category = await repo.category.add(c);
                categories.push(category);
            });

            productWithImagesAndCategories = { ...product, images, categories };
        });

        if (!created) return null;

        return productWithImagesAndCategories!;
    }

    async findById(id: string): Promise<ProductWithImagesAndCategories | null> {
        return Promise.resolve({} as ProductWithImagesAndCategories);
    }

    async delete(id: string): Promise<void> {}

    async update(
        id: string,
        data: CreateUpdateProductInterface
    ): Promise<void> {}
}
