## Tutorial de Firebase

1. registrarse en firebase

2. creamos el proyecto

3. instalamos el cli de firebase *esto ya esta dentro del docker*

```
npm install -g firebase-tools
```

4. creamos una base de datos 
   
```
cloud firestore -> crear database
``` 

5. obtener las credenciales y pegarlas en `services.js` 
    
```  
Proyecto -> Configuracion del proyecto -> general -> Firebase SDK snippet
```

1. deploy del proyecto al hosting de google 

```   
  - firebase login
  - firebase init
  - firebase deploy
```