FROM node:13

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm install
RUN npm update

COPY . .

EXPOSE 8081
EXPOSE 27017

cmd ["npm", "run", "dev"]