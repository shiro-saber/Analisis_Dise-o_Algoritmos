using UnityEngine;
using System.Collections;

public class mover : MonoBehaviour {
    public static float _spdMult = 1f;
    private int frames = 0;
    //protected Animator anim;
    public GameObject _cindy;
    Vector3 jump = new Vector3(0.0f, 300.0f, 0.0f);
    Vector3 jump2 = new Vector3(0.0f, 100.0f, 0.0f);
    bool InAir = false;
    public Quaternion kuz;
    public Vector3 sharmuta;
    public Quaternion debug;
    private Rigidbody rigido;
	// Use this for initialization
	void Start () {
        kuz = this.transform.rotation;
        sharmuta = this.transform.position;
        //rigido = this.GetComponent<Rigidbody>();
	}

    void OnCollisionEnter(Collision otro)
    {
        if (otro.gameObject.tag == "Untagged")
            InAir = false;
    }

    void OnCollisionExit(Collision otro)
    {
        InAir = true;
    }
     void mekai()
    {
        this.transform.position = sharmuta;
        this.transform.rotation = kuz;
        this.GetComponent<Rigidbody>().velocity = Vector3.zero;
        this.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
    }
    // Update is called once per frame
    void Update()
    {
        debug = this.transform.rotation;
        if (this.transform.rotation.z > 0.2f || this.transform.rotation.z < -0.2f)
        {
            mekai();
        }
        if (_cindy.CompareTag("raptor"))
        {
            if (Input.GetKey(KeyCode.UpArrow) && Input.GetKey(KeyCode.DownArrow) && InAir == false)
            {
                _cindy.GetComponent<Rigidbody>().AddForce(jump2);
                //print("deberia saltar, hacia adelante");
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = true;
                Raptor_Control._cindyAvanza = false;
            }
            else if (Input.GetKey(KeyCode.RightArrow))
            {
                //anim.Stop();
                //anim.CrossFade("Look_right", 0.2f);
                transform.Rotate(new Vector3(0f, 5f, 0f));
                //transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));

                Raptor_Control._rotaCindyDerecha = true;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = false;
            }
            else if (Input.GetKey(KeyCode.LeftArrow))
            {
                //transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                //anim.Stop();
                //anim.CrossFade("Look_left", 0.2f);
                transform.Rotate(new Vector3(0f, -5f, 0f));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = true;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = false;
            }
            if (Input.GetKey(KeyCode.RightArrow) && Input.GetKey(KeyCode.UpArrow))
            {
                //anim.Stop();
                //anim.CrossFade("Run", 0.2f);
                //anim.CrossFade("Look_right", 0.2f);
                transform.Rotate(new Vector3(0f, 1.5f, 0f));
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));

                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = true;
            }
            else if (Input.GetKey(KeyCode.LeftArrow) && Input.GetKey(KeyCode.UpArrow))
            {
                //anim.Stop();
                //anim.CrossFade("Run", 0.2f);
                //anim.CrossFade("Look_left", 0.2f);
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                transform.Rotate(new Vector3(0f, -1.5f, 0f));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = true;
            }
            else if (Input.GetKey(KeyCode.DownArrow) && InAir == false)
            {
                _cindy.GetComponent<Rigidbody>().AddForce(jump);
                print("deberia saltar");
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = true;
                Raptor_Control._cindyAvanza = false;
                
            }
            else if (Input.GetKey(KeyCode.UpArrow))
            {
                //anim.Stop();
                //anim.CrossFade("Run", 0.2f);
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = true;
            }
            else
            {
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = false;
            }

            if (_spdMult != 1)
            {
                frames++;
                if (frames >= 14000)
                {
                    _spdMult = 1f;
                    frames = 0;
                }
            } //esto hace al multiplicador de velocidad temporal
        }
        else if (_cindy.CompareTag("raptor2"))
        {

            if (Input.GetKey(KeyCode.D))
            {
                transform.Rotate(new Vector3(0f, 1.5f, 0f));
                //transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));

                Raptor_Control._rotaCindyDerecha = true;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = false;
            }
            else if (Input.GetKey(KeyCode.A))
            {
                //transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                transform.Rotate(new Vector3(0f, -1.5f, 0f));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = true;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = false;
            }
            if (Input.GetKey(KeyCode.D) && Input.GetKey(KeyCode.W))
            {
                transform.Rotate(new Vector3(0f, 1.5f, 0f));
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));

                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = true;
            }
            else if (Input.GetKey(KeyCode.A) && Input.GetKey(KeyCode.W))
            {
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                transform.Rotate(new Vector3(0f, -1.5f, 0f));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = true;
            }
            else if (Input.GetKey(KeyCode.S) && InAir == false)
            {
                _cindy.GetComponent<Rigidbody>().AddForce(jump);
                print("deberia saltar");
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = true;
                Raptor_Control._cindyAvanza = false;
                
            }
            else if (Input.GetKey(KeyCode.W))
            {
                transform.Translate(new Vector3(0f, 0f, 1f * _spdMult));
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = true;
            }
            else
            {
                Raptor_Control._rotaCindyDerecha = false;
                Raptor_Control._rotaCindyIzquierda = false;
                Raptor_Control._cindySalta = false;
                Raptor_Control._cindyAvanza = false;
            }

            if (_spdMult != 1)
            {
                frames++;
                if (frames >= 14000)
                {
                    _spdMult = 1f;
                    frames = 0;
                }
            } //esto hace al multiplicador de velocidad temporal
        }

    }
}
