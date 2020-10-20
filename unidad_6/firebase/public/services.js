import {firebaseConfig} from './env.js'

// Your web app's Firebase configuration
firebase.initializeApp(firebaseConfig);

// Initialize Firebase
const db = firebase.firestore();

const create = (data) => {
  return db.collection("users").add(data);
};

const update = (id, data) => {
  const recordRef = db.collection("users").doc(id);
  return recordRef.update(data);
};

const delet = (id) => {
  return db.collection("users")
  .doc(id)
  .delete()
}

const suscribe = (cb) => {
  return db.collection("users").onSnapshot(cb);
};

export default {
  create,
  update,
  delet,
  suscribe
}