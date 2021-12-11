//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//
//  smart_pointers.cpp
//
//  Smart pointers are essentially for automatic memory management
//  meaning that it does the new and delete for you.
//
//  Microsoft has good documentation on it:
//  https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-1701
//
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

#include <cstdio>
#include <memory>

class dummy
{
public:
    dummy(const char * name_) : m_name(name_) { printf("%s created\n", m_name); }
    ~dummy() { printf("%s destroyed\n", m_name); }

    void print_adr() { printf("%s: \t%p\n", m_name, this); }

private:
    const char* m_name;
};

class dummer : public dummy
{
};

int main()
{
    // unique_ptr
    {
        // It's member only has the raw pointer itself, so really no overhead going on.
        // It is mainly a replacement of 'auto_ptr' from the old c++ standard library.
        //  * Allows only ONE ownership of the underlying pointer
        //  * It can be moved to a new owner, but not shared or copied

        printf("-------- unique_ptr\n");

        // create a unique_ptr
        std::unique_ptr<dummy> unique_dummy = std::make_unique<dummy>("Unique Dummy");    // make_unique: c++14
        unique_dummy->print_adr();
#if 0
        // copy (prohibited)
        std::unique_ptr<dummy> unique_dummy_new = unique_dummy;    // compile error (deleted function)
#else
        // move ownership
        // but... try to stick to one object, it makes the logic complicated - Microsoft
        std::unique_ptr<dummy> unique_dummy_new = std::move(unique_dummy);
#endif
        // the former will no longer have the ownership
        // * the raw pointer is obtained by using the 'get()' function
        printf("unique_dummy:\t%p\n", unique_dummy.get());     // 0x0
        unique_dummy_new->print_adr();

    }   // free!
    printf("\n");


    // shared_ptr
    {
        // Used when multiple ownership is given to a single object in memory.
        // shared_ptr internally has two pointers:
        //  1) ptr to the object
        //  2) ptr to "Control Block" - a shared obj that manages the reference count data
        // Once the control block's ref count decrement reaches to 0, then it destroys the
        // memory resource and also itself

        printf("-------- shared_ptr\n");

        // If the pointer is going to be initialzed later, it is a good practice to
        // set a nullptr explicitly in the initialization.
        std::shared_ptr<dummy> shared_dummy(nullptr);

        // Init with make_shared
        // It's possible to init with new, but try to avoid that if you can
        shared_dummy = std::make_shared<dummy>("Shared Dummy");
        shared_dummy->print_adr();

        // Copy, second ownership, ref count +1
        auto shared_dummy_new = shared_dummy;
        shared_dummy_new->print_adr();

        // shared_ptr can be type casted using the following:
        // static_pointer_cast<>, dynamic_pointer_cast<>, and cons_pointer_cast<>
        std::shared_ptr<dummer> shared_dummer = std::static_pointer_cast<dummer>(shared_dummy);
        shared_dummer->print_adr();

    }   // free!
    printf("\n");


    // weak_ptr
    {
        // It is used in a case when you still need to reference to the shared_ptr but
        // without having an ownership. Several important features to know from this.

        printf("-------- weak_ptr\n");

        std::weak_ptr<dummy> weak_dummy;

        // expired(), use_count()
        // Checks if the referencing object is still valid. That is, reference count != 0,
        // which is obtained the latter function.
        {
            std::shared_ptr<dummy> shared_dummy = std::make_shared<dummy>("Dummy");
            weak_dummy = shared_dummy;

            printf("Dummy Expired? %d Count: %d\n", weak_dummy.expired(), weak_dummy.use_count());
            shared_dummy.reset();   // delete
            printf("Dummy Expired? %d Count: %d\n", weak_dummy.expired(), weak_dummy.use_count());
        }

        // lock():
        // Returns a shared_ptr to it's reference object IF it is not expired.
        {
            std::shared_ptr<dummy> shared_dummy = std::make_shared<dummy>("Dummy");
            weak_dummy = shared_dummy;
#if 0   // make it expired
            shared_dummy.reset();
#endif
            // this way of design lets you to depend on the availability of the referencing object
            if (std::shared_ptr<dummy> shared_dummy_created = weak_dummy.lock())
            {
                // notice that by creating a shared_ptr via lock() also INCREASED the reference count!
                printf("Dummy Count: %d Location: %p\n", weak_dummy.use_count(), shared_dummy_created.get());
            }
            else
                printf("Dummy Expired! Location: %p\n", shared_dummy_created.get());

            // tried simple check with the raw pointer, this also works obvously
            if (shared_dummy.get() != nullptr)
                printf("Dummy Count: %d Location: %p\n", weak_dummy.use_count(), shared_dummy.get());
        }
    }

    return EXIT_SUCCESS;
}