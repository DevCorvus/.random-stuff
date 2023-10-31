import { CategoryRepository } from '../features/category/category.repository';
import { CountryRepository } from '../features/country/country.repository';
import { ProductImageRepository } from '../features/product/images/product-image.repository';
import { ProductRepository } from '../features/product/product.repository';
import { UserRepository } from '../features/user/user.repository';
import { PostgresDatabase } from './postgres';

interface Repositories {
    user: UserRepository;
    country: CountryRepository;
    product: ProductRepository;
    productImage: ProductImageRepository;
    category: CategoryRepository;
}

export class UnitOfWork {
    constructor(private db: PostgresDatabase) {}

    async transaction(
        cb: (repo: Repositories) => Promise<void>
    ): Promise<boolean> {
        const client = await this.db.getClient();

        const repos: Repositories = {
            user: new UserRepository(client),
            country: new CountryRepository(client),
            product: new ProductRepository(client),
            productImage: new ProductImageRepository(client),
            category: new CategoryRepository(client),
        };

        let status: boolean;

        try {
            await client.query('BEGIN');
            await cb(repos);
            await client.query('COMMIT');
            status = true;
        } catch {
            await client.query('ROLLBACK');
            status = false;
        } finally {
            client.release();
        }

        return status;
    }
}
