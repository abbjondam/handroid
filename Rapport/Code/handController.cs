using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class handController : MonoBehaviour
{

    public Demo bluetoothScript;
    float speed = 0.1f;
    int[] orientation;

    public GameObject index_a;
    public GameObject index_b;
    public GameObject index_c;

    void Start()
    {
        GameObject bluetoothGameObject = GameObject.Find("Demo");
        bluetoothScript = bluetoothGameObject.GetComponent<Demo>();
    }

    void Update()
    {
        orientation = Array.ConvertAll<string, int>(bluetoothScript.subscribeText.text.Split(','),int.Parse);

        // Test to verify that Arduino Nano 33 BLE can control Unity hand model
        if (orientation[0] == 100)
        {
            Quaternion toRotation = Quaternion.Euler(0, 0, 0);
            index_a.transform.localRotation = Quaternion.Lerp(index_a.transform.localRotation, toRotation, Time.time * speed);
            index_b.transform.localRotation = Quaternion.Lerp(index_b.transform.localRotation, toRotation, Time.time * speed);
            index_c.transform.localRotation = Quaternion.Lerp(index_c.transform.localRotation, toRotation, Time.time * speed);
        }
        if (orientation[0] == 1000)
        {
            Quaternion toRotation = Quaternion.Euler(0, 0, -85);
            index_a.transform.localRotation = Quaternion.Lerp(index_a.transform.localRotation, toRotation, Time.time * speed);
            index_b.transform.localRotation = Quaternion.Lerp(index_b.transform.localRotation, toRotation, Time.time * speed);
            index_c.transform.localRotation = Quaternion.Lerp(index_c.transform.localRotation, toRotation, Time.time * speed);
        }

    }
}
