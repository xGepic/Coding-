FROM node:latest

EXPOSE 3000

RUN mkdir -p /app
ADD src /app/src
ADD public /app/public
ADD package-lock.json /app
ADD package.json /app
ADD .gitignore /app
ADD README.md /app

WORKDIR /app

RUN npm install

CMD [ "npm", "start" ]