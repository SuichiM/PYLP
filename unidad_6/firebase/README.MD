## Tutorial de Firebase

> CRUD simple con firebase, correr el docker de firebase `pylp_firebase` se levantará un server web local ->
> [localhost](http://localhost:3001/firebase/public/)

## Pasos:

1. registrarse en firebase

2. crear el proyecto

### paso extra si lo van a hacer fuera del docker

3. instalar el cli de firebase _esto ya esta dentro del docker_

```
npm install -g firebase-tools
```

4. creamos una base de datos

```
cloud firestore -> crear database
```

5. obtener las credenciales y pegarlas en `env.js`

```
Proyecto -> Configuracion del proyecto -> general -> Firebase SDK snippet
```

## Deploy del proyecto a la web

1. deploy del proyecto al hosting de google

```
  - firebase login
  - firebase init
  - firebase deploy
```
