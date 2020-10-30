import { firebaseConfig } from "./env.js";

// Your web app's Firebase configuration
firebase.initializeApp(firebaseConfig);

// Initialize Firebase
const db = firebase.firestore();

const create = (data, collection = "users") => {
  return db.collection(collection).add(data);
};

const update = (id, data, collection = "users") => {
  const recordRef = db.collection(collection).doc(id);
  return recordRef.update(data);
};

const delet = (id, collection = "users") => {
  return db.collection(collection).doc(id).delete();
};

const suscribe = (cb, collection = "users") => {
  return db.collection(collection).onSnapshot(cb);
};

export default {
  create,
  update,
  delet,
  suscribe,
};
