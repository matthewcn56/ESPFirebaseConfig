import { StatusBar } from 'expo-status-bar';
import React, {useState, useEffect, useCallback} from 'react';
import { StyleSheet, Text, View, TouchableOpacity, RefreshControl, ScrollView, SafeAreaView } from 'react-native';
import {db} from "./config/Firebase";

export default function App() {
  const [refreshing, setRefreshing] = React.useState(false);
  const [ledStatus, setLEDStatus] = useState(false);
  function updateLED(){
    db.ref("led1").set(
      !ledStatus
    );
  }

  function boolToString(val){
    if (val==true)
      return "true";
    if (val==false)
      return "false";
  }

  useEffect(() => {
    db.ref("led1").on('value', (querySnapshot) => {
      let led1Value = querySnapshot.val();
      setLEDStatus(led1Value);
    });
    console.log(ledStatus);
    console.log("Component mounted!!");

  }, []); //ComponentDidMount

  //update values when refreshing is done
  // useEffect(() => {
  //   if (refreshing ==true){
  //     db.ref("led1").on('value', (querySnapshot) => {
  //       let led1Value = querySnapshot.val();
  //       setLEDStatus(led1Value);
  //     });
  //     console.log(ledStatus);
  //     console.log("Component refreshed!!");
  //   }

  // }, [refreshing]); //After refreshed

  const wait = (timeout) => {
    return new Promise(resolve => {
      setTimeout(resolve, timeout);
    });
  }

const onRefresh = React.useCallback(() => {
    //READ FROM DATABASE HERE
setRefreshing(true);

wait(2000).then(() => setRefreshing(false));
}, []);

  return (
    
    <SafeAreaView style={styles.container}>
      <ScrollView contentContainerStyle ={styles.scrollView}
      refreshControl={
        <RefreshControl refreshing={refreshing} onRefresh={onRefresh} />
        }> 
        <Text>Open up App.js to start working on your app!</Text>
        <TouchableOpacity onPress= {updateLED}>
          <Text>Click to Toggle LED</Text>
        </TouchableOpacity>


        <Text>LED Is currently: {boolToString(ledStatus)}</Text>
        <StatusBar style="auto" />
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    display: "flex",
        backgroundColor: '#ffedd9',
        alignItems: 'center',
        justifyContent: 'center',
        flexDirection: "column",
        textAlign: "center"
  },
  scrollView: {
    flex: 1,
    alignItems: 'center',
    //justifyContent: 'flex-start',
    width: "100%"
  },
});
