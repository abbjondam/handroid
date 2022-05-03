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
    // Start is called before the first frame update
    void Start()
    {
        GameObject bluetoothGameObject = GameObject.Find("Demo");
        bluetoothScript = bluetoothGameObject.GetComponent<Demo>();
        // public string bluetoothVal = bluetoothScript.subscribeText.text;
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(bluetoothScript.subscribeText.text);
        Debug.Log("___");
        orientation = Array.ConvertAll<string, int>(bluetoothScript.subscribeText.text.Split(','),int.Parse);

        if (orientation[0] == 100)
        {
            Quaternion toRotation = Quaternion.Euler(0, 0, 0);
            index_a.transform.localRotation = Quaternion.Lerp(index_a.transform.localRotation, toRotation, Time.time * speed);
            index_b.transform.localRotation = Quaternion.Lerp(index_b.transform.localRotation, toRotation, Time.time * speed);
            index_c.transform.localRotation = Quaternion.Lerp(index_c.transform.localRotation, toRotation, Time.time * speed);
        }
        if (orientation[0] == 1000)
        {
            Quaternion toRotation = Quaternion.Euler(0, 0, -90);
            index_a.transform.localRotation = Quaternion.Lerp(index_a.transform.localRotation, toRotation, Time.time * speed);
            index_b.transform.localRotation = Quaternion.Lerp(index_b.transform.localRotation, toRotation, Time.time * speed);
            index_c.transform.localRotation = Quaternion.Lerp(index_c.transform.localRotation, toRotation, Time.time * speed);
        }

    }
}
