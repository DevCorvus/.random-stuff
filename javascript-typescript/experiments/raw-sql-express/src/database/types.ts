import { QueryResult } from 'pg';

export interface DatabaseInterface {
    query: (query: string, params?: any[]) => Promise<QueryResult<any>>;
}
