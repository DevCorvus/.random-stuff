CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = now();
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE EXTENSION IF NOT EXISTS "uuid-ossp";


DROP TABLE IF EXISTS users CASCADE;
DROP TABLE IF EXISTS roles;
DROP TABLE IF EXISTS countries;
DROP TABLE IF EXISTS products CASCADE;
DROP TABLE IF EXISTS product_images;
DROP TABLE IF EXISTS categories;
DROP TABLE IF EXISTS products_categories;

CREATE TABLE countries(
    id SERIAL,
    code VARCHAR(2) NOT NULL UNIQUE,
    name TEXT NOT NULL UNIQUE,
    PRIMARY KEY (id)
);

CREATE TABLE roles(
    id SERIAL,
    name TEXT NOT NULL UNIQUE,
    PRIMARY KEY (id)
);

CREATE TABLE users(
    id UUID DEFAULT uuid_generate_v4(),
    name TEXT NOT NULL,
    email TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    country_id INT NOT NULL,
    role_id INT NOT NULL,
    created_at TIMESTAMP DEFAULT now(),
    updated_at TIMESTAMP DEFAULT now(),
    PRIMARY KEY (id),
    FOREIGN KEY(country_id) REFERENCES countries(id),
    FOREIGN KEY(role_id) REFERENCES roles(id)
);

CREATE TRIGGER update_user_updated_at
BEFORE UPDATE ON users
FOR EACH ROW EXECUTE PROCEDURE update_updated_at_column();

CREATE TABLE products(
    id UUID DEFAULT uuid_generate_v4(),
    title TEXT NOT NULL,
    description TEXT,
    price INT NOT NULL,
    stock INT NOT NULL,
    created_at TIMESTAMP DEFAULT now(),
    updated_at TIMESTAMP DEFAULT now(),
    PRIMARY KEY (id)
);

CREATE TRIGGER update_product_updated_at
BEFORE UPDATE ON products
FOR EACH ROW EXECUTE PROCEDURE update_updated_at_column();

CREATE TABLE product_images(
    id UUID DEFAULT uuid_generate_v4(),
    product_id UUID NOT NULL,
    path TEXT NOT NULL,
    type TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT now(),
    PRIMARY KEY(id),
    FOREIGN KEY(product_id) REFERENCES products(id)
);

CREATE TABLE categories(
    id SERIAL,
    title TEXT NOT NULL UNIQUE,
    description TEXT,
    created_at TIMESTAMP DEFAULT now(),
    updated_at TIMESTAMP DEFAULT now(),
    PRIMARY KEY(id)
);

CREATE TRIGGER update_category_updated_at_column
BEFORE UPDATE ON categories
FOR EACH ROW EXECUTE PROCEDURE update_updated_at_column();

CREATE TABLE products_categories(
    product_id UUID REFERENCES products(id)
    category_id INT REFERENCES categories(id),
);

-- Seeding

INSERT INTO countries(code, name)
VALUES ('AF', 'Afghanistan'),
       ('AX', 'Aland Islands'),
       ('AL', 'Albania'),
       ('DZ', 'Algeria'),
       ('AS', 'American Samoa'),
       ('AD', 'Andorra'),
       ('AO', 'Angola'),
       ('AI', 'Anguilla'),
       ('AQ', 'Antarctica'),
       ('AG', 'Antigua and Barbuda'),
       ('AR', 'Argentina'),
       ('AM', 'Armenia'),
       ('AW', 'Aruba'),
       ('AU', 'Australia'),
       ('AT', 'Austria'),
       ('AZ', 'Azerbaijan'),
       ('BS', 'Bahamas'),
       ('BH', 'Bahrain'),
       ('BD', 'Bangladesh'),
       ('BB', 'Barbados'),
       ('BY', 'Belarus'),
       ('BE', 'Belgium'),
       ('BZ', 'Belize'),
       ('BJ', 'Benin'),
       ('BM', 'Bermuda'),
       ('BT', 'Bhutan'),
       ('BO', 'Bolivia'),
       ('BQ', 'Bonaire, Sint Eustatius and Saba'),
       ('BA', 'Bosnia and Herzegovina'),
       ('BW', 'Botswana'),
       ('BV', 'Bouvet Island'),
       ('BR', 'Brazil'),
       ('IO', 'British Indian Ocean Territory'),
       ('BN', 'Brunei Darussalam'),
       ('BG', 'Bulgaria'),
       ('BF', 'Burkina Faso'),
       ('BI', 'Burundi'),
       ('KH', 'Cambodia'),
       ('CM', 'Cameroon'),
       ('CA', 'Canada'),
       ('CV', 'Cape Verde'),
       ('KY', 'Cayman Islands'),
       ('CF', 'Central African Republic'),
       ('TD', 'Chad'),
       ('CL', 'Chile'),
       ('CN', 'China'),
       ('CX', 'Christmas Island'),
       ('CC', 'Cocos (Keeling) Islands'),
       ('CO', 'Colombia'),
       ('KM', 'Comoros'),
       ('CG', 'Congo'),
       ('CD', 'Congo, Democratic Republic of the Congo'),
       ('CK', 'Cook Islands'),
       ('CR', 'Costa Rica'),
       ('CI', 'Cote D''Ivoire'),
       ('HR', 'Croatia'),
       ('CU', 'Cuba'),
       ('CW', 'Curacao'),
       ('CY', 'Cyprus'),
       ('CZ', 'Czech Republic'),
       ('DK', 'Denmark'),
       ('DJ', 'Djibouti'),
       ('DM', 'Dominica'),
       ('DO', 'Dominican Republic'),
       ('EC', 'Ecuador'),
       ('EG', 'Egypt'),
       ('SV', 'El Salvador'),
       ('GQ', 'Equatorial Guinea'),
       ('ER', 'Eritrea'),
       ('EE', 'Estonia'),
       ('ET', 'Ethiopia'),
       ('FK', 'Falkland Islands (Malvinas)'),
       ('FO', 'Faroe Islands'),
       ('FJ', 'Fiji'),
       ('FI', 'Finland'),
       ('FR', 'France'),
       ('GF', 'French Guiana'),
       ('PF', 'French Polynesia'),
       ('TF', 'French Southern Territories'),
       ('GA', 'Gabon'),
       ('GM', 'Gambia'),
       ('GE', 'Georgia'),
       ('DE', 'Germany'),
       ('GH', 'Ghana'),
       ('GI', 'Gibraltar'),
       ('GR', 'Greece'),
       ('GL', 'Greenland'),
       ('GD', 'Grenada'),
       ('GP', 'Guadeloupe'),
       ('GU', 'Guam'),
       ('GT', 'Guatemala'),
       ('GG', 'Guernsey'),
       ('GN', 'Guinea'),
       ('GW', 'Guinea-Bissau'),
       ('GY', 'Guyana'),
       ('HT', 'Haiti'),
       ('HM', 'Heard Island and Mcdonald Islands'),
       ('VA', 'Holy See (Vatican City State)'),
       ('HN', 'Honduras'),
       ('HK', 'Hong Kong'),
       ('HU', 'Hungary'),
       ('IS', 'Iceland'),
       ('IN', 'India'),
       ('ID', 'Indonesia'),
       ('IR', 'Iran, Islamic Republic of'),
       ('IQ', 'Iraq'),
       ('IE', 'Ireland'),
       ('IM', 'Isle of Man'),
       ('IL', 'Israel'),
       ('IT', 'Italy'),
       ('JM', 'Jamaica'),
       ('JP', 'Japan'),
       ('JE', 'Jersey'),
       ('JO', 'Jordan'),
       ('KZ', 'Kazakhstan'),
       ('KE', 'Kenya'),
       ('KI', 'Kiribati'),
       ('KP', 'Korea, Democratic People''s Republic of'),
       ('KR', 'Korea, Republic of'),
       ('XK', 'Kosovo'),
       ('KW', 'Kuwait'),
       ('KG', 'Kyrgyzstan'),
       ('LA', 'Lao People''s Democratic Republic'),
       ('LV', 'Latvia'),
       ('LB', 'Lebanon'),
       ('LS', 'Lesotho'),
       ('LR', 'Liberia'),
       ('LY', 'Libyan Arab Jamahiriya'),
       ('LI', 'Liechtenstein'),
       ('LT', 'Lithuania'),
       ('LU', 'Luxembourg'),
       ('MO', 'Macao'),
       ('MK', 'Macedonia, the Former Yugoslav Republic of'),
       ('MG', 'Madagascar'),
       ('MW', 'Malawi'),
       ('MY', 'Malaysia'),
       ('MV', 'Maldives'),
       ('ML', 'Mali'),
       ('MT', 'Malta'),
       ('MH', 'Marshall Islands'),
       ('MQ', 'Martinique'),
       ('MR', 'Mauritania'),
       ('MU', 'Mauritius'),
       ('YT', 'Mayotte'),
       ('MX', 'Mexico'),
       ('FM', 'Micronesia, Federated States of'),
       ('MD', 'Moldova, Republic of'),
       ('MC', 'Monaco'),
       ('MN', 'Mongolia'),
       ('ME', 'Montenegro'),
       ('MS', 'Montserrat'),
       ('MA', 'Morocco'),
       ('MZ', 'Mozambique'),
       ('MM', 'Myanmar'),
       ('NA', 'Namibia'),
       ('NR', 'Nauru'),
       ('NP', 'Nepal'),
       ('NL', 'Netherlands'),
       ('AN', 'Netherlands Antilles'),
       ('NC', 'New Caledonia'),
       ('NZ', 'New Zealand'),
       ('NI', 'Nicaragua'),
       ('NE', 'Niger'),
       ('NG', 'Nigeria'),
       ('NU', 'Niue'),
       ('NF', 'Norfolk Island'),
       ('MP', 'Northern Mariana Islands'),
       ('NO', 'Norway'),
       ('OM', 'Oman'),
       ('PK', 'Pakistan'),
       ('PW', 'Palau'),
       ('PS', 'Palestinian Territory, Occupied'),
       ('PA', 'Panama'),
       ('PG', 'Papua New Guinea'),
       ('PY', 'Paraguay'),
       ('PE', 'Peru'),
       ('PH', 'Philippines'),
       ('PN', 'Pitcairn'),
       ('PL', 'Poland'),
       ('PT', 'Portugal'),
       ('PR', 'Puerto Rico'),
       ('QA', 'Qatar'),
       ('RE', 'Reunion'),
       ('RO', 'Romania'),
       ('RU', 'Russian Federation'),
       ('RW', 'Rwanda'),
       ('BL', 'Saint Barthelemy'),
       ('SH', 'Saint Helena'),
       ('KN', 'Saint Kitts and Nevis'),
       ('LC', 'Saint Lucia'),
       ('MF', 'Saint Martin'),
       ('PM', 'Saint Pierre and Miquelon'),
       ('VC', 'Saint Vincent and the Grenadines'),
       ('WS', 'Samoa'),
       ('SM', 'San Marino'),
       ('ST', 'Sao Tome and Principe'),
       ('SA', 'Saudi Arabia'),
       ('SN', 'Senegal'),
       ('RS', 'Serbia'),
       ('CS', 'Serbia and Montenegro'),
       ('SC', 'Seychelles'),
       ('SL', 'Sierra Leone'),
       ('SG', 'Singapore'),
       ('SX', 'Sint Maarten'),
       ('SK', 'Slovakia'),
       ('SI', 'Slovenia'),
       ('SB', 'Solomon Islands'),
       ('SO', 'Somalia'),
       ('ZA', 'South Africa'),
       ('GS', 'South Georgia and the South Sandwich Islands'),
       ('SS', 'South Sudan'),
       ('ES', 'Spain'),
       ('LK', 'Sri Lanka'),
       ('SD', 'Sudan'),
       ('SR', 'Suriname'),
       ('SJ', 'Svalbard and Jan Mayen'),
       ('SZ', 'Swaziland'),
       ('SE', 'Sweden'),
       ('CH', 'Switzerland'),
       ('SY', 'Syrian Arab Republic'),
       ('TW', 'Taiwan, Province of China'),
       ('TJ', 'Tajikistan'),
       ('TZ', 'Tanzania, United Republic of'),
       ('TH', 'Thailand'),
       ('TL', 'Timor-Leste'),
       ('TG', 'Togo'),
       ('TK', 'Tokelau'),
       ('TO', 'Tonga'),
       ('TT', 'Trinidad and Tobago'),
       ('TN', 'Tunisia'),
       ('TR', 'Turkey'),
       ('TM', 'Turkmenistan'),
       ('TC', 'Turks and Caicos Islands'),
       ('TV', 'Tuvalu'),
       ('UG', 'Uganda'),
       ('UA', 'Ukraine'),
       ('AE', 'United Arab Emirates'),
       ('GB', 'United Kingdom'),
       ('US', 'United States'),
       ('UM', 'United States Minor Outlying Islands'),
       ('UY', 'Uruguay'),
       ('UZ', 'Uzbekistan'),
       ('VU', 'Vanuatu'),
       ('VE', 'Venezuela'),
       ('VN', 'Viet Nam'),
       ('VG', 'Virgin Islands, British'),
       ('VI', 'Virgin Islands, U.s.'),
       ('WF', 'Wallis and Futuna'),
       ('EH', 'Western Sahara'),
       ('YE', 'Yemen'),
       ('ZM', 'Zambia'),
       ('ZW', 'Zimbabwe');

INSERT INTO roles(name) VALUES('user'), ('admin');

/*
INSERT INTO users(name, email, password, country_id, role_id)
VALUES('fulano', 'fulano@example.com', '12345678',
    (SELECT id FROM countries WHERE code = 'VE'),
    (SELECT id FROM roles WHERE name = 'admin')
);

INSERT INTO products(title, description, price, stock)
VALUES('Shoes', 'Just shoes', 10000, 4);
*/
